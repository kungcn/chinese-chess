<template>
<div id="setting-header">
  <div id="setting-back"
       @click="goBack()"
       @touchend="setBackBtn(false)"
       @touchstart="setBackBtn(true)">
    <img :src="img.back_btn" v-if="status.bck" />
    <img :src="img.back_btn_press" v-else />
  </div>
  <div id="setting-header-user"
       class="background-container"
       :style="{ backgroundImage: 'url(' + img.userbg + ')' }">
    <div id="setting-header-user-portrait"
         @touchstart="setUsrBtn(true)"
         @touchend="setUsrBtn(false)"
         @click="showBottomPopup()">
       <img v-if="img.usr"
            :src="img.usr"
            class="center" />
       <div class="center"
            v-if="status.usr"></div>
    </div>
    <p>{{ usrAccount }}</p>
  </div>
</div>
</template>

<script>
import { mapGetters } from 'vuex'

export default {
  props: [ 'usrAccount', 'portraitIndex' ],
  data() {
    return {
      img: {
        userbg: require('@/assets/pages/UserSetting/header-user.png'),
        back_btn_press: require('@/assets/pages/UserSetting/back_btn_press.png'),
        back_btn: require('@/assets/pages/UserSetting/back_btn.png'),
        usr: null
      },
      status: {
        bck: false,
        usr: false
      }
    }
  },
  created: function() {
    this.setCurrPortrait();
  },
  computed: {
    ...mapGetters({
      portrait: 'getPortrait',
    })
  },
  watch: {
    'portraitIndex': 'setCurrPortrait'
  },
  methods: {
    // TODO
    goBack() {
      console.log('返回主页');
    },
    setBackBtn(status) {
      this.status.bck = status;
    },
    setUsrBtn(status) {
      this.status.usr = status;
    },
    setCurrPortrait() {
      this.img.usr = this.portrait.items[this.portraitIndex];
    },
    showBottomPopup() {
      this.$store.commit('setPopupStatus', { name: 'portrait', value: true });
    }
  }
}
</script>

<style>
#setting-header {
  position: relative;
  width: 100%;
  height: 18vh;
}
#setting-header-user {
  height: 18vh; width: 18vh;
  position: absolute;
  left: 50%;
  transform: translate(-50%, 0);
  background: no-repeat;
  background-size: 100% 100%
}
#setting-back {
  position: absolute;
  height: 6vh; width: 6vh;
  border-radius: 100%;
  left: 2vw; top: 2vw;
  cursor: pointer;
}
#setting-back > img {
  height: 100%; width: 100%;
}
#setting-header-user-portrait {
  position: absolute;
  width: 55%; height: 55%;
  left: 50%; top: 5%;
  border-radius: 100%;
  transform: translate(-50%, 0);
  background-color: #d0b399
}
#setting-header-user-portrait > img {
  width: 90%; height: 90%;
  border-radius: 100%;
}
#setting-header-user-portrait > div {
  width: 100%; height: 100%;
  border-radius: 100%;
  background-color: rgba(0, 0, 0, 0.3)
}
#setting-header-user > p {
  position: relative;
  height: 25%;
  color: #d0b399;
  margin: 0;
  text-align: center;
  top: 63%;
}
</style>