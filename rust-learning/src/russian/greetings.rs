pub use ::english::greetings;

pub fn hi() -> String {
	println!("from english {}", greetings::hi());
	"Дарова!".to_string()
}
