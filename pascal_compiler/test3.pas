{ test suite, test integral types and operations on them }
program test(input, output);
var
   i	 : integer;
   float : real;
begin
   i :=0;
   float:=0.1;
   while i<3 do
   begin
      i:=i+1;
      float:=float+(i/float)
   end
end. 
   

