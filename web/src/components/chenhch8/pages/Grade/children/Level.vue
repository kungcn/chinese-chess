<template>
<div id="grade-level">
  <v-small-tag :msg="tag.msg"
               :addClass="tag.class">
  </v-small-tag>
  <v-form :msg="form"></v-form>
  <p @click="levelInstruction()">等级说明</p>
</div>
</template>

<script>
import { getLevelInfo } from '../../../service/utils'
import vForm from './Form'
import vSmallTag from '../../../comm/SmallTag'

export default {
  props: [ 'grade' ],
  components: {
    vForm, vSmallTag
  },
  data() {
    return {
      tag: { msg: '', class: null },
      form: ''
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
      };
      this.form = this.grade + '积分/';
      if (level.goal)
        this.form += `${level.goal.name}${level.goal.grade}积分`;
      else
        this.form += level.goal.name;
    }
  }
}
</script>

<style>
#grade-level {
  width: 100%;
  height: auto;
}
#grade-level > p {
  color: #5d5c56;
  margin: 0;
  text-decoration: underline;
}
</style>