<template>
    <canvas id="chessCanvas"></canvas>
</template>

<script>
    export default {
        computed: {
            
        },
        mounted() {
            let Chess = window.Chess = (id) => {
                this.canvas.w = this.canvas.w || document.body.clientWidth;
                this.init(id);
            }
            let chess = new Chess("chessCanvas");
            chess.renderChess(true);

            Chess.prototype = {
                canvas: {
                    w: 0,
                    h: 1000
                },
                board: {
                    cellSize: 100, // 一个格子大小
                    lineWidth: 2, // 画笔大小
                    strokeStyle: '#000', // 画笔颜色
                    markLength: 30, // 标记长度
                    markPadding: 10 // 标记间距
                },
                init: (id) => {
                    let that = this;
                    that.bodys = [];
                    that.element = document.getElementById(id);
                    that.element.width = that.canvas.w;
                    that.element.height = that.canvas.h;
                    that.ctx = that.element.getContext("2d");

                    that.render();
                },
                render: () => {
                    this.bindevent();
                },
                drawBoard: () => {
                    let that = this;
                    let ctx = that.ctx;
                    let bodys = that.bodys;
                    let r = 9;
                    let c = 8;
                    let cellSize = that.board.cellSize;
                    let w = cellSize * c;
                    let h = r * cellSize;
                    let startX = (that.canvas.w - w) / 2;
                    let startY = (that.canvas.h - h) / 2;
                    let cX = 0;
                    let cY = 0;
                    let rX = 0;
                    let rY = 0;

                    ctx.beginPath();
                    ctx.lineWidth = that.board.lineWidth;
                    ctx.strokeStyle = that.board.strokeStyle;

                    that.board.w = w;
                    that.board.h = h;

                    that.startX = startX;
                    that.startY = startY;
                    that.radius = cellSize / 2;
                    that.maxR = r;
                    that.maxC = c;

                    for (let i = 0; i <= r; i++) {
                        cX = startX;
                        cY = startY + (i * cellSize);
                        ctx.moveTo(cX, cY);
                        cxt.lineTo(cX + w, cY);

                        bodys[i] = bodys[i] || [];
                        for (let k = 0; k <= c; k++) {
                            rx = startX + (k * cellSize);
                            rY = startY + (i * cellSize);

                            bodys[i][k] = bodys[i][k] || {};
                            bodys[i][k].x = rX;
                            bodys[i][k].y = rY;
                            bodys[i][k].r = i;
                            bodys[i][k].c = k;

                            if (i == 4 && k != 0 && k != 8 || i == 9) {
                                continue;
                            }
                            ctx.moveTo(rX, cY);
                            ctx.lineTo(rX, rY + cellSize);
                        }
                    }

                    ctx.stroke();
                    ctx.restore();
                    let fontOffsetY = bodys[4][0].y + that.radius;
                    ctx.fillStyle = "#000";
                    ctx.font = "bold 40px Arial";
                    ctx.textBaseline = "middle";


                    ctx.fillText("汉", startX + cellSize, fontOffsetY);
                    ctx.fillText("界", startX + cellSize * 2, fontOffsetY);
                    ctx.fillText("楚", startX + cellSize * 5, fontOffsetY);
                    ctx.fillText("河", startX + cellSize * 6, fontOffsetY);
                    ctx.save();

                    ctx.beginPath();
                    ctx.strokeStyle = "#000";
                    ctx.lineWidth = 2;
                    ctx.moveTo(bodys[0][3].x, bodys[0][3].y);
                    ctx.lineTo(bodys[2][5].x, bodys[2][5].y);
                    ctx.moveTo(bodys[0][5].x, bodys[0][5].y);
                    ctx.lineTo(bodys[2][3].x, bodys[2][3].y);


                    ctx.moveTo(bodys[7][3].x, bodys[7][3].y);
                    ctx.lineTo(bodys[9][5].x, bodys[9][5].y);
                    ctx.moveTo(bodys[7][5].x, bodys[7][5].y);
                    ctx.lineTo(bodys[9][3].x, bodys[9][3].y);


                    ctx.stroke();

                    function drawTopLeft(x, y, l, o) {
                       var s = x - o - l, e = s + l, c = y - o;
                       ctx.moveTo(s, c);
                       ctx.lineTo(e, c);
                       ctx.lineTo(e, c - l);
                   }
                   function drawTopRight(x, y, l, o) {
                       var s = x + o + l, e = s - l, c = y - o;
                       ctx.moveTo(s, c);
                       ctx.lineTo(e, c);
                       ctx.lineTo(e, c - l);
                   }
                   function drawBottomLeft(x, y, l, o) {
                       var s = x - o - l, e = s + l, c = y + o;
                       ctx.moveTo(s, c);
                       ctx.lineTo(e, c);
                       ctx.lineTo(e, c + l);
                   }
                   function drawBottomRight(x, y, l, o) {
                       var s = x + o + l, e = s - l, c = y + o;
                       ctx.moveTo(s, c);
                       ctx.lineTo(e, c);
                       ctx.lineTo(e, c + l);
                   }


                   function drawX(r, c, pos) {
                       var x = bodys[r][c].x,
                           y = bodys[r][c].y;
                       ctx.beginPath();
                       ctx.lineWidth = 3;
                       ctx.strokeStyle = "#000";
                       if (pos[0]) {
                           drawTopLeft(x, y, that.qipan.markLen, that.qipan.markPadding);
                       }
                       if (pos[1]) {
                           drawTopRight(x, y, that.qipan.markLen, that.qipan.markPadding);
                       }
                       if (pos[2]) {
                           drawBottomLeft(x, y, that.qipan.markLen, that.qipan.markPadding);
                       }
                       if (pos[3]) {
                           drawBottomRight(x, y, that.qipan.markLen, that.qipan.markPadding);
                       }
                       ctx.stroke();


                   }
                   drawX(2, 1, [1, 1, 1, 1]);
                   drawX(2, 7, [1, 1, 1, 1]);


                   drawX(3, 0, [0, 1, 0, 1]);
                   drawX(3, 2, [1, 1, 1, 1]);
                   drawX(3, 4, [1, 1, 1, 1]);
                   drawX(3, 6, [1, 1, 1, 1]);
                   drawX(3, 8, [1, 0, 1, 0]);


                   drawX(7, 1, [1, 1, 1, 1]);
                   drawX(7, 7, [1, 1, 1, 1]);


                   drawX(6, 0, [0, 1, 0, 1]);
                   drawX(6, 2, [1, 1, 1, 1]);
                   drawX(6, 4, [1, 1, 1, 1]);
                   drawX(6, 6, [1, 1, 1, 1]);
                   drawX(6, 8, [1, 0, 1, 0]);


                   ctx.beginPath();
                   ctx.lineWidth = 5;
                   ctx.rect(startX - 5, startY - 5, w + 10, h + 10);
                   ctx.stroke();


                }
            },
            renderChessboard: (redBottom) => {
                let chessboard = this.chessboard = [
                   ['车', '马', '相', '仕', '帅', '仕', '相', '马', '车'],
                   [],
                   ['', '炮', '', '', '', '', '', '炮', ''],
                      ['兵', '', '兵', '', '兵', '', '兵', '', '兵'],
                   [],
                   [],
                       ['卒', '', '卒', '', '卒', '', '卒', '', '卒'],
                   ['', '炮', '', '', '', '', '', '炮', ''],
                   [],
                   ['車', '馬', '象', '士', '将', '士', '象', '馬', '車'],
                ];
            }
        },
        data() {
            return {
                
            }
        },
        methods: {
            
        },
        watch: {
            
        }
    }
</script>

<style scoped>
    
</style>