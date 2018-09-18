extern crate rust_learning as rl;

fn main() {
	println!("{}", rl::english::greetings::hi());
	println!("{}", rl::russian::greetings::hi());
	
	rl::structs::print_struct();

	println!("matches:");
	rl::matches::match_num(5);
	rl::matches::match_num(9);

	rl::matches::match_msg(rl::matches::Msg::Point(34.123123, 54.231312));
	rl::matches::match_msg(rl::matches::Msg::Quit);

	let p = rl::generics::takes_anything(5);
}
