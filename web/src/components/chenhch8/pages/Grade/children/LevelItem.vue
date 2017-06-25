<template>
<div class="level-item">
  <div class="level-item-title">
    <span :style="{ color: this.color }">
      {{ title }}
    </span>
  </div>
  <div>
    <div v-for="item in items">
      <div class="level-item-content">
        <p>
          <v-small-tag :msg="item.msg"
                       :addClass="item.class">
          </v-small-tag>
          <span>{{ item.grade }}积分</span>
        </p>
      </div>
    </div>
  </div>
</div>
</template>

<script>
import vSmallTag from '../../../comm/SmallTag'

export default {
  props: [ 'title', 'color', 'items' ],
  components: {
    vSmallTag
  }
}
</script>

<style>
.level-item {
  width: 100%;
  height: auto;
  padding-top: 2vh;
  display: flex;
  padding: 1vh 7vw;
}
.level-item > div {
  height: auto;
}
.level-item > div:nth-child(1) {
  flex: 1;
  position: relative;
}
.level-item-title > span {
  position: absolute;
  left: 50%; top: 50%;
  transform: translate(-50%, -50%);
  letter-spacing: 2.5px;
  font-size: 4.5vw;
}
.level-item > div:nth-child(2) {
  flex: 3;
}
.level-item-content {
  margin: 1.5vh 0;
}
.level-item-content > p {
  margin: 0;
  padding: 0 5px;
  position: relative;
}
.level-item-content > p > span {
  position: absolute;
  display: inline-block;
  right: 0;
  top: 50%;
  transform: translate(0, -50%);
  font-size: 4.5vw;
  color: #64615b;
  letter-spacing: 2.5px;
}
</style>