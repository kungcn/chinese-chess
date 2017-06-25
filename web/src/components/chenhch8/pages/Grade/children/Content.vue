<template>
<div id="setting-content">
  <div id="setting-content-container">

    <v-level :grade="user.gameDetail.grade"></v-level>

  </div>
</div>
</template>

<script>
import vLevel from './Level'

export default {
  components: {
    vLevel
  },
  props: [ 'user' ]
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
</style>