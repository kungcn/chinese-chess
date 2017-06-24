<template>
<div>
  <mu-toast v-if="toast" :message="msg"/>
</div>
</template>

<script>
import { mapGetters } from 'vuex'

export default {
  computed: {
    ...mapGetters({
      toast: 'getToastPopupStatus',
      msg: 'getToastMessage'
    })
  },
  watch: {
    toast: function() {
      this.setToast();
    }
  },
  data() {
    return {
      toastTimer: null
    }
  },
  methods: {
    setToast() {
      if (this.toastTimer) clearTimeout(this.toastTimer);
      this.toastTimer = setTimeout(() => {
        this.$store.commit('setPopupStatus', { name: 'toast', value: false })
      }, 1000)
    }
  }
}
</script>