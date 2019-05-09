# Tetris

## 框体

## 成绩

- int

## 名称

- 8位char数组

## 下一个方块

- int 储存type

## 记录已有行

- 大小12*22的int数组

## 当前方块及其方向、位置

- struct包括四个int x,y,direction,type
  - x,y为整数
  - direction 0，1，2，3依次为0°，90°，180°，270°

## 保存时需写入的数据

- 成绩
- 名称
- 记录当前行的链表

## 颜色标准

- 0 无

- 1 浅蓝

- 2 蓝

- 3 橙

- 4 黄

- 5 绿

- 6 紫

- 7 红

## 类型标准

### 类型与颜色对应

- 0 无

- 1 □□□□

- 2 □ <br>&nbsp;&nbsp; □□□
  
- 3 &nbsp;&nbsp;&nbsp;&nbsp;□ <br>&nbsp;&nbsp;&nbsp;□□□

- 4 □□<br>&nbsp;&nbsp;&nbsp;□□

- 5 &nbsp;&nbsp;&nbsp;□□<br>&nbsp;&nbsp;&nbsp;□□

- 6 &nbsp;&nbsp;□ <br>&nbsp;&nbsp;&nbsp;□□□

- 7 □□<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;□□

## 方向数组

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;（6）<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;（3）&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;（5）&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;（7）<br>
（2）（1）（0\4\8\12）（9）（10）<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;（15）&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;（13）&nbsp;&nbsp;&nbsp;&nbsp;（11）<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;（14）<br>

## 键盘回调函数

- refreshdisplay

- 方向键
  - 上 顺时针旋转
  - 下 快速下落
  - 左 向左移动
  - 右 向右移动

- 空格 直接落到底

- Esc 暂停

## 定时器回调函数

- refreshdisplay