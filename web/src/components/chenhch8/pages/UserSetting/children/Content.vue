<template>
<div id="setting-content">
  <div id="setting-content-container">

  <v-form :items="form1" class="form-item"></v-form>
  <v-form :items="form2" class="form-item"></v-form>
  <v-form :items="form3" class="form-item"></v-form>

  </div>
</div>
</template>

<script>
import vForm from '../../../comm/Form'

export default {
  components: {
    vForm
  },
  props: [ 'user' ],
  data() {
    return {
      form1: null,
      form2: null,
      form3: null
    }
  },
  watch: {
    user: {
      handler: function() {
        this.assign();
      },
      deep: true
    }
  },
  created: function() {
    this.assign();
  },
  methods: {
    openPopup(name, data = null) {
      self = this;
      return function() {
        if (name == 'dialog') {
          self.$store.commit('setDialogInfo', data);
        }
        self.$store.commit('setPopupStatus', { name: name, value: true })
      }
    },
    assign() {
      this.form1 = [
        { title: '游戏ID', text: this.user.id },
        {
          title: '我的等级', text: this.user.level,
          callback: (function(self) {
            return function() {
              self.$router.push({ name: 'Grade' })
            }
          })(this)
        },
        {
          title: '昵称', text: this.user.name,
          callback: this.openPopup('dialog', {
            title: '昵称',
            text: this.user.name,
            type: 'name',
            default: '未命名'
          })
        }
      ],
      this.form2 = [
        {
          title: '性别', text: this.user.gender,
          callback: this.openPopup('gender')
        }, {
          title: '地区', text: (this.user.region.province != this.user.region.city) ? this.user.region.province + this.user.region.city : this.user.region.city,
          callback: this.openPopup('region')
        }, {
          title: '个性签名', text: this.user.sign.substring(0, 5) + '...',
          callback: this.openPopup('dialog', {
            title: '个性签名',
            text:  this.user.sign,
            type: 'sign',
            default: '这人很懒，什么都没留下'
          })
        }
      ],
      this.form3 = [
        { title: '手机', text: this.user.phone || '未绑定' }
      ]
    }
  }
}
</script>

<style>
#setting-content {
  position: relative;
  width: 100%;
  height: 80vh;
}
#setting-content-container {
  position: relative;
  width: 78%;
  max-height: 95%;
  height: auto;
  margin: 0 auto;
  overflow-y: auto;
  overflow-x: none;
  padding: 4%;
}
.form-item {
  margin-bottom: 5vh;
}

</style>