# uart
 
uart 分包问题，部分MCU会产生现象较严重的分包现象，现象为30ms左右

## 

使用\r\n结束符断帧，add a time 50 - 100 ms to solve the unhandle packet with no split char.