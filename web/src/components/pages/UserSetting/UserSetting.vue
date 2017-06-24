<template>
<div id="user-setting"
     :style="{ backgroundImage: 'url(' + img + ')' }"
     class="background-container">
  <v-header
    :usrAccount="user.name"
    :portraitIndex="user.portrait"></v-header>
  <v-content :user="user"></v-content>
  <v-portrait-chose></v-portrait-chose>
  <v-gender-chose></v-gender-chose>
  <v-region-chose></v-region-chose>
  <v-dialog></v-dialog>
  <v-toast></v-toast>
</div>
</template>

<script>
import vHeader from './children/Header'
import vContent from './children/Content'
import vPortraitChose from './children/PortraitChose'
import vGenderChose from './children/GenderChose'
import vRegionChose from './children/RegionChose'
import vDialog from './children/Dialog'
import vToast from './children/Toast';
import { mapGetters } from 'vuex'

export default {
  components: {
    vHeader, vContent, vPortraitChose, vGenderChose,
    vRegionChose, vDialog, vToast
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