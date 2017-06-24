<template>
<mu-popup position="bottom"
    popupClass="gender-chose"
    :open="status"
    @close="close()" >
  <div id="gender-chose-popup"
       class="background-container"
       :style="{ backgroundImage: 'url(' + bgUrl + ')' }">

    <div class="gender-chose-btn background-container"
         :style="{ backgroundImage: 'url(' + bgBtn + ')' }"
         @touchstart="currPos = 1"
         @touchend="currPos = -1"
         @click="setGender('男')">
      <p>
        <span>
          <img src="../../../../../assets/pages/UserSetting/man.png">
          <span>男</span>
        </span>
      </p>
      <div class="btn-active" v-if="currPos == 1"></div>
    </div>

    <div class="gender-chose-btn background-container"
         :style="{ backgroundImage: 'url(' + bgBtn + ')' }"
         @touchstart="currPos = 2"
         @touchend="currPos = -1"
         @click="setGender('女')">
      <p>
        <span>
          <img src="../../../../../assets/pages/UserSetting/woman.png">
          <span>女</span>
        </span>
      </p>
      <div class="btn-active" v-if="currPos == 2"></div>
    </div>

    <div class="gender-chose-btn background-container"
         :style="{ backgroundImage: 'url(' + bgBtn + ')' }"
         @touchstart="currPos = 3"
         @touchend="currPos = -1"
         @click="setGender('保密')">
      <p>
        <span>
          <img src="../../../../../assets/pages/UserSetting/private.png">
          <span>保密</span>
        </span>
      </p>
      <div class="btn-active" v-if="currPos == 3"></div>
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
      bgBtn: require('@/assets/pages/UserSetting/menu_btn_normal.png'),
      bgBtn2: require('@/assets/pages/UserSetting/menu_btn_press.png'),
      currPos: -1
    }
  },
  computed: {
    ...mapGetters({
       status: 'getGenderPopupStatus'
    })
  },
  methods: {
    close() {
      this.$store.commit('setPopupStatus', { name: 'gender', value: false });
    },
    setGender(gender) {
      this.$store.commit('setUserInfo', { gender });
      this.close();
      this.$store.commit('setToastMessage', '修改成功');
      this.$store.commit('setPopupStatus', { name: 'toast', value: true });
    }
  }
}
</script>

<style>
.gender-chose {
  width: 100%; height: 35%;
  background-color: transparent !important;
}
#gender-chose-popup {
  position: relative;
  width: 100%;
  height: 100%;
  padding: 9% 9vw 0 9vw;
  display: flex;
  flex-direction: column;
}
#gender-chose-popup > div {
  position: relative;
  flex: 1;
  display: flex;
}
.gender-chose-btn {
  position: relative;
  width: 100%;
  margin: 0 auto;
}
.gender-chose-btn p {
  flex: 1;
  text-align: center;
}
.gender-chose-btn p > span {
  display: inline-block;
  height: 80%;
  left: 50%;
  top: 50%;
  //justify-content: center;
}
.gender-chose-btn span > img {
  height: 100%;
  display: inline-block
}
.gender-chose-btn span > span {
  position: absolute;
  top: 50%;
  margin-left: 5vw;
  transform: translate(0, -50%);
  font-size: 2rem;
}
.btn-active {
  position: absolute;
  left: 4%;
  width: 92%;
  height: 90%;
  background-color: rgba(0, 0, 0, 0.1);
}
</style>