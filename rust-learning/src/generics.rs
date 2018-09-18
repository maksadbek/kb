pub enum Option<T> {
	Some(T),
	None,
}

pub enum Result<T, E> {
	Ok(T),
	Err(E),
}

pub fn takes_anything<T>(x: T) {
	println!("{}", x);
}

pub struct Point<T> {
	x: T,
	y: T,
}

pub impl<T> Point<T> {
	fn swap(&mut self) {
		std::mem::swap(&mut self.x, &mut self.y);
	}
}
