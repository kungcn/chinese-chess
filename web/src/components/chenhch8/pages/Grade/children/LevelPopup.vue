<template>
<mu-popup position="bottom"
    popupClass="level-popup"
    :open="status"
    @close="close()" >
  <div id="level-popup"
       class="background-container"
       :style="{ backgroundImage: 'url(' + bgUrl + ')' }">

    <div>
      <h1 id="level-popup-title">棋力等级说明</h1>
    </div>

    <div>
      <p id="level-popup-describe">
        棋力等级评测对照国家象棋棋力评测系统，每次会匹配和你起立相当的对手与你对局，在每个级别中净赢同等级别的对手会晋级。此等级评测系统评测出来的棋力等级，具有极高的权威性。
      </p>
    </div>
    
    <div>
      <v-level-item
        v-for="(v, i) in titles"
        :key="i"
        :title="titles[i]"
        :color="colors[i]"
        :items="items[i]"></v-level-item>
    </div>

  </div>
    
</mu-popup>
</template>

<script>
import { mapGetters } from 'vuex'
import { getLevelInfo } from '../../../service/utils';

import vLevelItem from './LevelItem';

export default {
  components: {
    vLevelItem
  },
  data() {
    return {
      bgUrl: require('@/assets/pages/UserSetting/dialog_bg_1.png'),
      titles: [],
      colors: [],
      items: []
    }
  },
  computed: {
    ...mapGetters({
      status: 'getLevelPopupStatus'
    })
  },
  created: function() {
    this.setLevelItem();
  },
  methods: {
    close() {
      this.$store.commit('setPopupStatus', { name: 'level', value: false });
    },
    setLevelItem() {
      let level = getLevelInfo();
      Object.keys(level).forEach(key => {
        this.titles.push(key);
        this.colors.push(level[key]['color'])
        let tmp = []
        Object.keys(level[key]).forEach(key2 => {
            if (key2 == 'color') return;
            tmp.push({
              grade: level[key][key2],
              msg: key2,
              class: {
                position: 'relative',
                top: '50%',
                backgroundColor: level[key]['color']
              }
           })
        })
        this.items.push(tmp);
      })
    }
  }
}
</script>

<style>
.level-popup {
  width: 100%; height: 90%;
  background-color: transparent !important;
}
#level-popup {
  position: relative;
  width: 100%;
  height: 100%;
  padding-top: 8.5vh;
  display: flex;
  flex-direction: column;
}
#level-popup > div {
  width: 85vw;
  margin: 0 auto;
}
#level-popup > div:nth-child(1) {
  flex: 1;
  border-bottom: 1px solid #d4c3b1;
}
#level-popup > div:nth-child(2) {
  flex: 2;
  border-bottom: 1px solid #d4c3b1;
}
#level-popup > div:nth-child(3) {
  flex: 6;
}
#level-popup-title {
  position: relative;
  font-weight: 100;
  font-size: 3.5vh;
  color: #514f4d;
  text-align: center;
  margin: 0;
  top: 50%;
  transform: translate(0, -50%);
}
#level-popup-describe {
  color: #64615b;
  font-size: 2.2vh;
  line-height: 4vh;
  letter-spacing: 2.5px;
  margin: 0;
  position: relative;
  top: 50%;
  transform: translate(0, -50%);
  cursor: pointer;
}
</style>