# Chinese Chess
## Introduction
A project called Yi-like(弈乎) to do Chinese chess game on Web, Android and PC both. In web part, we use Vue 2.0 and webpack to help us finish the job while in PC part we use OpenGL. Meanwhile, socket is necessary for us to play games with others at the same time.

弈乎是我们在Web端,安卓端以及PC端均有的多平台中国象棋博弈游戏.

"圍棊也。从廾亦聲。"----<说文解字>

弈,虽然一开始指的是围棋.但如今而言,想起博弈,除了棋还有很多其他的事情.但是最能代表博弈本身的,无非就是中国象棋.

### Memebers
sorted by the first name.

Haicheng Chen(陈海城): working on Web & frontend.

Wenhan Chen(陈文汉): working on Web.

Zilin Chen(陈梓麟): working on backend.

Junning Gong(龚俊宁): working on Web.

Zekun Ye(叶泽坤): working on Web.

Hao Zhang(张昊): working on PC.

### Code Rules in Front End
1. Api放在与components同级的api文件夹下index.js文件内。
2. components下放置的是可重用的组件，views文件下放置的是各路由指向的页面。
3. css文件内规范如下：
```
//  xxx.css
<style scoped>
.xxx-nav {
}
</style>
```
需要添加scoped属性，类名加上前缀，涉及UI框架内部样式修改时，可以在/static/css/reset.css内修改，但需要注释写明使用在了哪些文件内。当UI框架样式修改时，需要注意scoped属性是否影响了其使用。
4. 文件在起始处需要注明以下注释：
```
//  @author kungcn
//  create at 2017.06.13
//  function: nav
```
5. 修改他人文件时需要在旁注明以下注释：
```
//  @author kungcn
//  update at 2017.06.13
//  why to update and how to update
```
6. 每一次发起PR前先引入eslint测试，确保代码规范(需要将error设置为warning的提出来讨论后再设置，这个很坑的嘛)

## Lisence
MIT Lisence

## How to run in Web?
```
//  node must over 6.x
npm install -g node

//  vue must over 2.x
npm install -g vue

npm install -g webpack

cd targetFolder(like ~/kcn/ChineseChess)

npm install

npm run dev
```
