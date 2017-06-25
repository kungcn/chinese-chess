<template>
<div id="small-tag"
     :style="addClass">
  {{ msg }}
</div>
</template>

<script>
export default {
  props: [ 'msg', 'addClass' ]
}
</script>

<style>
#small-tag {
  width: 15vw;
  height: 5vw;
  line-height: 5vw;
  border-radius: 6px;
  color: #e1d2bf;
  font-size: 3vw;
}
</style>