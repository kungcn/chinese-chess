<template>
<div id="user-setting"
     :style="{ backgroundImage: 'url(' + img + ')' }"
     class="background-container">
  <v-header
    :canClick="true"
    :usrAccount="user.name"
    :portraitIndex="user.portrait"></v-header>
  <v-content :user="user"></v-content>
  <v-portrait-chose></v-portrait-chose>
  <v-gender-chose></v-gender-chose>
  <v-region-chose></v-region-chose>
  <v-setting-dialog></v-setting-dialog>
  <v-toast></v-toast>
</div>
</template>

<script>
import vHeader from '../../comm/Header'
import vContent from './children/Content'
import vPortraitChose from './children/PortraitChose'
import vGenderChose from './children/GenderChose'
import vRegionChose from './children/RegionChose'
import vSettingDialog from './children/SettingDialog'
import vToast from '../../comm/Toast';
import { mapGetters } from 'vuex'

export default {
  components: {
    vHeader, vContent, vPortraitChose, vGenderChose,
    vRegionChose, vSettingDialog, vToast
  },
  computed: {
    ...mapGetters({
      user: 'getUserInfo'
    })
  },
  data() {
    return {
      img: require('@/assets/pages/UserSetting/bg.png')
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
.center {
  position: absolute;
  left: 50%; top: 50%;
  transform: translate(-50%, -50%);
}
.background-container {
  background: no-repeat;
  background-size: 100% 100%
}
</style>