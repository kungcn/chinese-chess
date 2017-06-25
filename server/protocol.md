# 通信协议
客户端与服务端使用socket通信，通信报文为json格式。

1. 客户端与服务端连接后，首先发送

```js
{
	name: "user_name"
}
```
之后服务端响应

```js
{
	self: {
		fd: number,
		name: "user_name"
	}.
	list: [{fd: number, name: "user_name"， playing: bool},{},{}]
}
```
2. 之后客户端根据1中服务端返回的list来选择与谁对战。报文格式为

```js
{
	send_to_fd: number // number被邀请客户的fd
}
```
	而此时对手会收到如下报文

```js
{
	recv_from_fd: number // number为发起邀请客户的fd
}
```
3. 如果对手接受，则向服务端发送

```js
{
	accept:true, 
	recv_from_fd: number // number为发起邀请者的fd
}
```
此后，邀请者和被邀请者会分别随机收到

```js
{first: true} || {first: false} //表示先手或后手 
```
	

如果被邀请者拒绝则向服务端发送

```js
{
	accept:false
}
```
此时发起邀请者会收到

```js
{
	accept:false
}
```

4. 对局开始，轮到自己回合的客户端向服务端发送

```js
{
	before_x: number,
	before_y: number,
	after_x: number,
	after_y: number
} // 代表棋手将(before_x, before_y)的棋子移动到(after_x, after_y)
```
服务端会自动判断是否合法，如果合法则服务端返回

```js
{
	ok: true
}
```
并向对手转发上述的移动报文。

否则返回

```js
{
	ok: false
}
```
	所以轮到对手回合则等待服务端转发对手的移动报文。
5. 如果某步棋导致胜利则胜利方会收到

```js
{
	win:true
}
```
败方则会收到

```js
{
	win:false
}
```
6. 客户端可以发送

```js
{
	get_list: true
}
```
来获得

```js
{
	list: [{fd: number, name: "user_name"， playing: bool}, {}, {}]
}
```
7. 如果比赛中途对手下线了会导致整个战局退出。此时己方会收到

```js
{
	opp_quit:true
}
```

8. 如果发起邀请后想取消邀请，则向服务器发送

```js
{
	cancel: true
}
```
而被邀请的对手同时也会收到

```js
{
	cancel: true
}
```


## 注意事项 

移动报文中的坐标是以先手为下方。即:

```c++
  chess_type m[10][9]; //棋盘的数据结构，m[0]这边是后手方，m[9]这边是先手方。
  m[9][4]; //为先手的帅的位置
  m[0][4]; //为后手的帅的位置 
```

## JSON报文例子

```js
{"name": "dylan"}
{"name": "kuer"}
{"send_to_fd": 5}
{"cancel": true}
{"accept": true, "recv_from_fd": 4} 
{"accept": false}
{"before_x": 9, "before_y": 4, "after_x": 8, "after_y": 4}
{"ok": true}
{"get_list": true}

```
