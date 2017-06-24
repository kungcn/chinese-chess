<template>
<div id="user-setting"
     :style="{ backgroundImage: 'url(' + img + ')' }"
     class="background-container">
  <v-header
    :usrAccount="user.account"></v-header>
  <v-content></v-content>
  <v-bottom-popup></v-bottom-popup>
</div>
</template>

<script>
import vHeader from './children/Header'
import vContent from './children/Content'
import vBottomPopup from './children/BottonPopup'

export default {
  components: {
    vHeader, vContent,  vBottomPopup
  },
  data() {
    return {
      img: require('@/assets/pages/UserSetting/bg.png'),
      user: {
        type: 1,
        account: '陈海城'
      }
    }
  }
}
</script>

<style>
#user-setting {
  position: absolute;
  width: 100%; height: 100%;
  font-size: 2rem;
}
.background-container {
  background: no-repeat;
  background-size: 100% 100%
}
.center {
  position: absolute;
  left: 50%; top: 50%;
  transform: translate(-50%, -50%);
}
</style>