<template>
<div>
  <mu-toast v-if="toast" message="设置成功"/>
</div>
</template>

<script>
import { mapGetters } from 'vuex'

export default {
  created: function() {
    this.$on('show-toast', this.showToast)
  },
  computed: {
    ...mapGetters({
      toast: 'getToastPopupStatus'
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