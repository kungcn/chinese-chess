<template>
<div id="user-setting" 
:style="{ backgroundImage: 'url(' + img + ')' }"
class="background-container">
  <v-header
    :usrAccount="user.name"
    :portraitIndex="user.portrait"></v-header>
  <v-Content></v-Content>

</div>
</template>

<script>
import { mapGetters } from 'vuex'

import vHeader from '../../comm/Header'
import vContent from './children/Content'

export default {
  components: {
    vHeader, vContent
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

</style>
