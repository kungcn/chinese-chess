<template>
<div id="setting-content">
  <div id="setting-content-container">

  <v-form :items="form1" class="form-item"></v-form>
  <v-form :items="form2" class="form-item"></v-form>

  </div>
</div>
</template>

<script>
import vForm from './Form'

export default {
  components: {
    vForm
  },
  props: [ 'level', 'usrAccount' ],
  data() {
    return {
      form1: [
        {
          title: '我的等级',
          text: '九级棋士(150)'
        },
        {
          title: '昵称',
          text: '叶泽坤'
        }
      ],
      form2: [
        {
          title: '性别',
          text: '男'
        },
        {
          title: '地区',
          text: '广东省'
        },
        {
          title: '个性签名',
          text: '这人很懒，...'
        }
      ]
    }
  }
}
</script>

<style>
#setting-content {
  position: relative;
  width: 100%;
  height: 82vh;
}
#setting-content-container {
  position: relative;
  width: 78%;
  height: 100%;
  margin: 0 auto;
  padding: 4%;
}
.form-item {
  margin: 5vh 0;
}

</style>