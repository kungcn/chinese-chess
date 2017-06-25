<template>
<div id="setting-content">
  <div id="setting-content-container">

    <v-level :grade="user.gameDetail.grade"></v-level>

  </div>

  <div id="setting-content-detail">
    <v-detail :data="user.gameDetail.month"></v-detail>
  </div>

</div>
</template>

<script>
import vLevel from './Level'
import vDetail from './Detail'

export default {
  components: {
    vLevel, vDetail
  },
  props: [ 'user' ]
}
</script>

<style>
#setting-content {
  position: relative;
  width: 100%;
  height: 80vh;
  display: flex;
  flex-direction: column;
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
#setting-content > div:nth-child(2) {
  padding: 0 6vw;
}
#setting-content-detail {
  flex: 1;
}
</style>