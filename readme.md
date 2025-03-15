# 自己用的小工具集合

### Hex2Ascii
16进制转字符串，支持unicode字符

### Ascii2Hex
字符串转16进制

### CheckEndian
检测当前是大小端

### RamTest
占用指定内存，可用作内存压力测试

### DiskTest
反复写入随机数到文件，可用作硬盘寿命测试
```bash
# 用法 DiskTest {写入文件的路径} {写入的数据量/M}
./DiskTest "/data/test.bin" 1024
# 如上，写入1G文件数据到 /data/test.bin
```

### Linear11Trans
Linear11 格式转换为实数

### Linear16Trans
Linear16 格式转换为实数

### ByteAcc
DediProg 工具中 ByteACC 校验算法异步实现
> Algorithm Description:   
> Sum the data bytes byte by byte and disregard any carry beyond 32 bits. 

### RandomMac
生成随机Mac地址 

### DateTimeCalc
时间戳加减运算
```bash
# 用法 DateTimeCalc {时间点} +/- {时间间隔}
./DateTimeCalc "2025-3-16 00:00:09" "-" "00:01:01"
# 将输出 2025-3-16 00:00:09 - 00:01:01 = 2025-03-15 23:59:08
./DateTimeCalc "2025-3-16 00:00:09" "+" "00:01:01"
# 将输出 2025-3-16 00:00:09 + 00:01:01 = 2025-03-16 00:01:10
```