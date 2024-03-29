auto swapping(int _value_a, int _value_b) -> void{
  Serial.println(String(F("First_value: ")) + String(_value_a));
  Serial.println(String(F("Second_value: ")) + String(_value_b));
  int temp {0};
  temp = _value_a;
  _value_a = _value_b;
  _value_b = temp;
  Serial.println(String(F("First_value: ")) + String(_value_a));
  Serial.println(String(F("Second_value: ")) + String(_value_b));
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);

  // int a {10};
  // int* ptr_a {&a};
  // a = 11;   //Direct accessing
  // *ptr_a = 11;    //indirect accessing
  int value_a = 100;
  int value_b = 200;

  swapping(value_a, value_b);
  Serial.println(*ptr_a);

}

void loop() {
  // put your main code here, to run repeatedly:

}
