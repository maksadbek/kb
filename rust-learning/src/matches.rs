pub enum Msg {
	Quit,
	Point(f64, f64),
}

pub fn match_msg(m: Msg) {
	match m {
		Msg::Quit => println!("this is quit"),
		Msg::Point(lon, lat) => println!("{}, {}", lon, lat),
	}
}

pub fn match_num(x: i32) {
	match x {
		1 => println!("one"),
		2 => println!("two"),
		3 => println!("three"),
		4 => println!("four"),
		5 => println!("four"),
		_ => println!("HZ")
	}
}
