# Tetris

## 框体

## 成绩

- long long

## 名称

- 8位char数组

## 下一个方块

- int 储存type

## 链表记录已有行

- struct为大小12的int数组

## 当前方块及其方向、位置

- struct包括四个int x,y,direction,type

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

- 2 □ </br>&nbsp;&nbsp; □□□
  
- 3 &nbsp;&nbsp;&nbsp;&nbsp;□ </br>&nbsp;&nbsp;&nbsp;□□□

- 4 □□</br>&nbsp;&nbsp;&nbsp;□□

- 5 &nbsp;&nbsp;&nbsp;□□</br>&nbsp;&nbsp;&nbsp;□□

- 6 &nbsp;&nbsp;□ </br>&nbsp;&nbsp;&nbsp;□□□

- 7 □□</br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;□□

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