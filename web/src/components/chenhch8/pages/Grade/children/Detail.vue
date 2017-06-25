<template>
<div id="grade-detail">
  <div id="grade-detail-btn-list">
    <div v-for="(btn, index) in btns"
         :key="index"
         @click="setActive(index)">
      <v-form :msg="btn"
              :active="index == curr"
              :addClass="active_class"></v-form>
    </div>
  </div>
  <div id="grade-detail-circle">

    <div id="grade-detail-circle-bg">
      <mu-circular-progress 
        mode="determinate"
        :strokeWidth="18"
        :size="150" 
        :color="'#d1c8b7'"
        :value="100"/>

      <div id="grade-detail-circle-annotation">
        <p>胜率</p>
        <p>{{ value2 }}%</p>
      </div>

    </div>

    <mu-circular-progress 
      mode="determinate"
      :strokeWidth="18"
      :size="150" 
      :color="'#c7594a'"
      :value="value"/>
  </div>
  <div id="grade-detail-info">
    <div v-for="(record, index) in records">
      <p>{{ record }}</p>
      <p>{{ nums[index] }}局</p>
    </div>
  </div>
</div>
</template>

<script>
import vForm from '../../../comm/Form'

export default {
  components: {
    vForm
  },
  props: [ 'data' ],
  data() {
    return {
      btns: [ '本月战绩', '上月战绩', '总战绩'],
      records: [ '胜利', '败北', '和棋' ],
      nums: [ 0, 0, 0 ],
      curr: 0,
      value: 0,
      value2: 0,
      active_class: {
        borderColor: 'rgba(0, 0, 0, 0.1)',
        borderWidth: '5px'
      }
    }
  },
  created: function() {
    this.setActive(0)
  },
  methods: {
    setActive(index) {
      this.curr = index;
      let key;
      if (index == 0)
        key = 'curr';
      else if (index == 1)
        key = 'last';
      else
        key = 'all';
      this.nums = [ this.data[key]['win'], this.data[key]['loss'], this.data[key]['tie'] ];
      this.value2 = (this.data[key]['win'] / (this.data[key]['win'] + this.data[key]['loss'] + this.data[key]['tie'])).toFixed(2);
      this.value = this.value2 * 100;
    }
  }
}
</script>

<style>
#grade-detail {
  width: 100%;
  height: 90%;
  margin-top: 3vh;
  display: flex;
  flex-direction: column;
}
#grade-detail-btn-list {
  display: flex;
  justify-content: space-around;
  flex: 1;
}
#grade-detail-btn-list > div {
  flex: 1;
}
#grade-detail-btn-list > div:nth-child(2) {
  margin: 0 1vw;
}
.grade-detail-btn-active {
  
}
#grade-detail-circle {
  flex: 2;
}
#grade-detail-info {
  width: 100%;
  flex: 1;
  display: flex;
}
#grade-detail-info > div {
  flex: 1;
}
#grade-detail-info > div:nth-child(2) {
  border-left: 1px solid #cfc2af;
  border-right: 1px solid #cfc2af;
}
#grade-detail-info p {
  margin: 1px;
  font-size: 2rem;
}
#grade-detail-circle-bg {
  position: absolute;
  left: 50%;
  transform: translate(-50%, 0);
}
#grade-detail-circle-annotation {
  position: absolute;
  width: 10vh; height: 10vh;
  left: 50%; top: 46%;
  transform: translate(-50%, -50%);
}
#grade-detail-circle-annotation > p {
  margin: 0;
  font-size: 3vh;
  color: #6e6a62;
}
</style>