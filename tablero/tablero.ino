float x=0.1; // velocidad de respuesta
int y,z,u,d,c,m,p,o;
void cero();
void uno();
void dos();
void tres();
void cuatro();
void cinco();
void seis();
void siete();
void ocho();
void nueve();
void vel( int z);
void setup() {
  pinMode(5 ,  OUTPUT); // led
  pinMode(6 ,  OUTPUT); // marcha
  pinMode(7 ,  OUTPUT); // centenas
  pinMode(8 ,  OUTPUT); // decenas
  pinMode(9 ,  OUTPUT); // unidades
  pinMode(10,  OUTPUT); // A
  pinMode(11,  OUTPUT); // B
  pinMode(12,  OUTPUT); // C
  pinMode(13,  OUTPUT); // D
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  y=1500; // ojo lectura de datos
  o=1500;
}
void loop() {
  y=o;
  u = y % 10;
  y = (y-u)/10;
  d = y % 10;
  y = (y-d)/10;
  c = y % 10;
  y = (y-c)/10;
  m = y % 10;
  if(d>=6)
  {
    d=5;
    o=o-40;
  }
  vel(m);
  digitalWrite(6, HIGH);
  delay(x);
  digitalWrite(6, LOW);
  delay(x);
  vel (c);
  digitalWrite(7, HIGH);
  delay(x);
  digitalWrite(7, LOW);
  delay(x); 
  vel (d);
  digitalWrite(8, HIGH);
  delay(x);
  digitalWrite(8, LOW);
  delay(x); 
  vel (u);
  digitalWrite(9, HIGH);
  delay(x);
  digitalWrite(9, LOW);
  delay(x);
  p++;
  if(p==3160)
  {
    p=0;
    o--;
    if(o==0)
    {
      while(1)
      {
        digitalWrite(5, HIGH);
      }
    }
  }
}
void vel(int z){
  switch (z) {
    case 0:
    cero();
    break;
    case 1:
    uno();
    break;
    case 2:
    dos();
    break;
    case 3:
    tres();
    break;
    case 4:
    cuatro();
    break;
    case 5:
    cinco();
    break;
    case 6:
    seis();
    break;
    case 7:
    siete();
    break;
    case 8:
    ocho();
    break;
    case 9:
    nueve();
    break;
  }
}
void cero(){
  digitalWrite(10, LOW); // 1
  digitalWrite(11, LOW); // 2
  digitalWrite(12, LOW); // 4
  digitalWrite(13, LOW); // 8
}
void uno(){
  digitalWrite(10, HIGH); // 1
  digitalWrite(11, LOW); // 2
  digitalWrite(12, LOW); // 4
  digitalWrite(13, LOW); // 8
}
void dos(){
  digitalWrite(10, LOW); // 1
  digitalWrite(11, HIGH); // 2
  digitalWrite(12, LOW); // 4
  digitalWrite(13, LOW); // 8
}
void tres(){
  digitalWrite(10, HIGH); // 1
  digitalWrite(11, HIGH); // 2
  digitalWrite(12, LOW); // 4
  digitalWrite(13, LOW); // 8
}
void cuatro(){
  digitalWrite(10, LOW); // 1
  digitalWrite(11, LOW); // 2
  digitalWrite(12, HIGH); // 4
  digitalWrite(13, LOW); // 8
}
void cinco(){
  digitalWrite(10, HIGH); // 1
  digitalWrite(11, LOW); // 2
  digitalWrite(12, HIGH); // 4
  digitalWrite(13, LOW); // 8
}
void seis(){
  digitalWrite(10, LOW); // 1
  digitalWrite(11, HIGH); // 2
  digitalWrite(12, HIGH); // 4
  digitalWrite(13, LOW); // 8
}
void siete(){
  digitalWrite(10, HIGH); // 1
  digitalWrite(11, HIGH); // 2
  digitalWrite(12, HIGH); // 4
  digitalWrite(13, LOW); // 8
}
void ocho(){
  digitalWrite(10, LOW); // 1
  digitalWrite(11, LOW); // 2
  digitalWrite(12, LOW); // 4
  digitalWrite(13, HIGH); // 8
}
void nueve(){
  digitalWrite(10, HIGH); // 1
  digitalWrite(11, LOW); // 2
  digitalWrite(12, LOW); // 4
  digitalWrite(13, HIGH); // 8
}
