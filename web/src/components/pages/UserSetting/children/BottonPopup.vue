<template>
<mu-popup position="bottom"
    popupClass="popup-bottom"
    :open="status"
    @close="close()" >
  <div id="bottom-popup"
       class="background-container"
       :style="{ backgroundImage: 'url(' + bgUrl + ')' }">
    <div>
      <div id="bottom-popup-currPortrait">
        <img :src="currPortrait.img" />
      </div>
    </div>

    <div>
      <ul id="protrait-list">
        <li v-for="(item, index) in portrait.items">
          <img :src="item"
               @click="setPortrait(index)" />
        </li>
      </ul>
    </div>

    <div>
      <div class="protrait-btn btn-sure"
           @click="makeSure()">
        <p class="center">确定</p>
      </div>
      <div class="protrait-btn btn-cancel"
          @click="close()">
        <p class="center">取消</p>
      </div>
    </div>
  </div>
    
</mu-popup>
</template>

<script>
import { mapGetters } from 'vuex'

export default {
  data() {
    return {
      bgUrl: require('@/assets/pages/UserSetting/dialog_bg_1.png'),
      currPortrait: { index: -1, img: null }
    }
  },
  created: function() {
    this.setCurrPortrait();
  },
  computed: {
    ...mapGetters({
      status: 'getBottomPopupStatus',
      portrait: 'getPortrait',
      curPortraitIndex: 'getPortraitIndex'
    })
  },
  methods: {
    close() {
      this.$store.commit('setBottomPopup', false);
      this.setCurrPortrait();
    },
    setCurrPortrait() {
      this.currPortrait.img = this.portrait.items[this.curPortraitIndex];
      this.currPortrait.index = this.curPortraitIndex;
    },
    setPortrait(index) {
      this.currPortrait.img = this.portrait.items[index];
      this.currPortrait.index = index;
    },
    makeSure() {
      this.$store.commit('setPortrait', this.currPortrait.index);
      setTimeout(this.close, 100);
    }
  }
}
</script>

<style>
.popup-bottom {
  width: 100%; height: 60%;
  background-color: transparent !important;
}
#bottom-popup {
  position: relative;
  width: 100%;
  height: 100%;
  padding-top: 10%;
}
#bottom-popup > div {
  position: relative;
  width: 100%;
  height: 34%;
  padding: 0 10%;
}
#bottom-popup-currPortrait {
  width: 30vw;
  height: 100%;
  margin: 0 auto;
}
#bottom-popup-currPortrait > img {
  display: block;
  bottom: 0;
  width: 26vw;
  height: 26vw;
  border-radius: 100%;
  box-shadow: 0 0 1vw 1.5vw #d0b399;
  position: absolute;
  left: 50%; bottom: -3vw;
  transform: translate(-50%, 0);
}
#bottom-popup > div:nth-child(2) {
  min-height: 20vw;
}
#protrait-list {
  display: flex;
  overflow-x: auto;
  width: 100%;
  height: 100%;
  padding: 0;
}
#protrait-list > li {
  list-style-type: none;
  display: inline-block;
  height: 100%;
  margin: auto 2vw;
  justify-content: center;
}
#protrait-list > li > img {
  display: block;
  width: 16vw;
  height: 16vw;
  border-radius: 100%;
  box-shadow: 0 0 1vw 1vw #d0b399;
  margin-top: 50%;
}
.protrait-btn {
  position: relative;
  width: 100%;
  height: 35%;
  border: 1px solid gray;
  border-radius: 5px;
}
.protrait-btn:nth-child(1) {
  margin-bottom: 8px;
}
.protrait-btn > p {
  margin: 0;
  text-align: center;
  font-size: 2rem;
}
.btn-sure {
  background-color: #45a54e
}
.btn-cancel {
  background-color: #bd7f5a
}
</style>