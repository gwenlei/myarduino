import processing.serial.*;
Serial duankou;
float x,y,xo,yo;
float data,d;
void setup(){
  duankou=new Serial(this,"COM6",9600);
xo=20;
yo=580;
x=20;
y=580;
  
size(800, 600);
background(255);
}
void draw(){
fill(255, 255, 255);
line(20,20,20,580);
line(20,580,780,580);
  if(duankou.available()>0)
  {
    data=duankou.read();
    println(int(data));
  }
  x=x+1;
  y=580-map(data,110,140,20,580);
  if(x>=780){
    x=20;
    y=580;
    xo=20;
    yo=580;
    background(255);
  }
  line(xo,yo,x,y);
  xo=x;
  yo=y;
}