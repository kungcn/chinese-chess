<template>
<mu-popup position="bottom"
    popupClass="level-popup"
    :open="status"
    @close="close()" >
  <div id="level-popup"
       class="background-container"
       :style="{ backgroundImage: 'url(' + bgUrl + ')' }">

  </div>
    
</mu-popup>
</template>

<script>
import { mapGetters } from 'vuex'

export default {
  data() {
    return {
      bgUrl: require('@/assets/pages/UserSetting/dialog_bg_1.png')
    }
  },
  computed: {
    ...mapGetters({
      status: 'getLevelPopupStatus'
    })
  },
  methods: {
    close() {
      this.$store.commit('setPopupStatus', { name: 'level', value: false });
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
  padding-top: 10%;
}
</style>