<template>
<mu-popup position="bottom"
    popupClass="gender-chose"
    :open="status"
    @close="close()" >
  <div id="gender-chose-popup"
       class="background-container"
       :style="{ backgroundImage: 'url(' + bgUrl + ')' }">
    <div>
      <div class="gender-chose-btn background-container"
           :style="{ backgroundImage: 'url(' + bgBtn + ')' }">

      </div>
    </div>

    <div>
      <div class="gender-chose-btn background-container"
           :style="{ backgroundImage: 'url(' + bgBtn + ')' }">
      </div>
    </div>

    <div>
      <div class="gender-chose-btn background-container"
           :style="{ backgroundImage: 'url(' + bgBtn + ')' }">
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
      bgBtn: require('@/assets/pages/UserSetting/menu_btn_normal.png'),
      bgBtn2: require('@/assets/pages/UserSetting/menu_btn_press.png')
    }
  },
  created: function() {
    
  },
  computed: {
    ...mapGetters({
       status: 'getGenderPopupStatus'
    })
  },
  methods: {
    close() {
      this.$store.commit('setPopupStatus', { name: 'gender', value: false });
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
}
.gender-chose-btn {
  position: relative;
  width: 100%;
  height: 90%;
  margin: 0 auto;
}
</style>