<template>
<div id="grade-level" @click="levelInstruction()">
  <v-small-tag :msg="tag.msg"
               :addClass="tag.class">
  </v-small-tag>
</div>
</template>

<script>
import { getLevelInfo } from '../../../service/utils'
import vForm from '../../../comm/Form'
import vSmallTag from '../../../comm/SmallTag'

export default {
  props: [ 'grade' ],
  components: {
    vForm, vSmallTag
  },
  data() {
    return {
      tag: { msg: '', class: null },

    }
  },
  created: function() {
    this.setValue();
  },
  methods: {
    levelInstruction() {
      this.$store.commit('setPopupStatus', { name: 'level', value: true })
    },
    setValue() {
      let level = getLevelInfo(this.grade);
      this.tag.msg = level.name;
      this.tag.class = {
        backgroundColor: level.color,
        marginLeft: 'auto',
        marginRight: 'auto',
        transform: 'translate(0, -1.5vh)'
      }
    }
  }
}
</script>

<style>
#grade-level {
  width: 100%;
  height: 18vh;
  border: 1px solid grey;
}
.test {
  background-color: #656d81;
}
</style>