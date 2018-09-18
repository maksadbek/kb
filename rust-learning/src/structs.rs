struct Point {
	x: i32,
	y: i32,
}

struct PointRef<'a> {
	x: &'a mut i32,
	y: &'a mut i32,
}

pub fn print_struct() {
	let mut point = Point{ x: 0, y: 0};
	{
		let r = PointRef{ x: &mut point.x, y: &mut point.y };

		*r.x = 5;
		*r.y = 6;
	}
	
	println!("{}", point.x);
	println!("{}", point.y);

	assert_eq!(5, point.x);
	assert_eq!(6, point.y);
}
