<template>
<div id="user-setting" 
:style="{ backgroundImage: 'url(' + img + ')' }"
class="background-container">
  <v-header
    :usrAccount="user.name"
    :portraitIndex="user.portrait"></v-header>
  <v-Content :user="user"></v-Content>
  <v-level-popup></v-level-popup>
</div>
</template>

<script>
import { mapGetters } from 'vuex'

import vHeader from '../../comm/Header'
import vContent from './children/Content'
import vLevelPopup from './children/LevelPopup'

export default {
  components: {
    vHeader, vContent, vLevelPopup
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
.background-container {
  background: no-repeat;
  background-size: 100% 100%
}
</style>
