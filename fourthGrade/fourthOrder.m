clc;
clear all;
close all;
format long

%original tranfer function
Gs = tf([0.003445 0.015159 0.016537],[1 1.4500000 0.777500 0.182375 0.015750]);
Gz = c2d(Gs,0.01);

Gs1 = tf([0.003445],[1 0.25]);
Gz1 = c2d(Gs1,0.1)

Gs2 = tf([1],[1 0.35]);
Gz2 = c2d(Gs2,0.1)

Gs3 = tf([1 1.99928],[1 0.4]);
Gz3 = c2d(Gs3,0.1)

Gs4 = tf([1 2.40101],[1 0.45]);
Gz4 = c2d(Gs4,0.1)

GsT = Gs1*Gs2*Gs3*Gs4;
GzT = Gz1*Gz2*Gz3*Gz4;

step(Gs,Gz,GsT,GzT);
