
a=[7.2, 8.84605, 10.6579, 12.6355, 14.7789, 17.0882, 19.5632, 22.2039, 25.0105, 27.9829, 31.1211, 34.425, 37.8947, 41.5303, 45.3316, 49.2987, 53.4316, 57.7303, 62.1947, 66.825, 71.6211, 76.5829, 81.7105, 87.0039, 92.4632, 98.0882]; %a数据y值 
b=[3.76285,4.61071, 5.10928,5.54212,6.11751,6.90122,7.28211,7.85498,8.33149,8.75359,9.71369,10.5935,11.529,12.8447,13.7972,14.6065,15.5978,16.7514,18.1946,19.8173,20.935 ,21.9714,22.9404,23.5531,24.531,24.6558]; %b数据y值 
c=[24.6141,24.4702,24.4483,24.4646,24.4345,24.4341,24.4185,24.3841,24.4531,24.3608,24.3844,24.3024,24.3082,24.2974,24.2715,24.2412,24.2364,24.1978,24.2381,24.1468,24.0959,24.083,24.1186,24.0304,23.9948,24.0054];
plot(a,b,'-*b',a,c,'-or'); %线性，颜色，标记 

axis([0,110,0,30]) %确定x轴与y轴框图大小 
set(gca,'XTick',[0:10:100]) %x轴范围1-6，间隔1 
set(gca,'YTick',[0:3:30]) %y轴范围0-700，间隔100 
legend('LOCALALGO','GLOBALALGO'); %右上角标注 
xlabel('percent(%)') %x轴坐标描述 
ylabel('time（s）') %y轴坐标描述

