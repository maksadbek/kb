package main

import (
	"errors"
	"log"
	"os"
	"os/signal"
	"time"
)

var (
	ErrTimeout   = errors.New("received timeout")
	ErrInterrupt = errors.New("received interrupt")
)

type Runner struct {
	interrupt chan os.Signal
	complete  chan error
	timeout   <-chan time.Time
	tasks     []func(int)
}

func New(d time.Duration) *Runner {
	return &Runner{
		interrupt: make(chan os.Signal, 1),
		complete:  make(chan error),
		timeout:   time.After(d),
	}
}

func (r *Runner) Add(tasks ...func(int)) {
	r.tasks = append(r.tasks, tasks...)
}

func (r *Runner) Start() error {
	signal.Notify(r.interrupt, os.Interrupt)
	go func() {
		r.complete <- r.run()
	}()

	select {
	case err := <-r.complete:
		return err
	case <-r.timeout:
		return ErrTimeout
	}
}

func (r *Runner) run() error {
	for id, task := range r.tasks {
		if r.gotInterrupt() {
			return ErrInterrupt
		}
		task(id)
	}
	return nil
}

func (r *Runner) gotInterrupt() bool {
	select {
	case <-r.interrupt:
		signal.Stop(r.interrupt)
		return true
	default:
		return false
	}
}

const timeout = 3 * time.Second

func main() {
	log.Println("Starting work.")

	r := New(timeout)

	r.Add(
		createTask(),
		createTask(),
		createTask(),
	)

	if err := r.Start(); err != nil {
		switch err {
		case ErrTimeout:
			log.Println("Terminating due to timeout.")
			os.Exit(1)
		case ErrInterrupt:
			log.Println("Terminating due to interrupt.")
			os.Exit(2)
		}
	}

	log.Println("Process ended.")
}

func createTask() func(int) {
	return func(id int) {
		log.Printf("Processor - Task #%d.", id)
		time.Sleep(time.Duration(id) * time.Second)
	}
}
