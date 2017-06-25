<template>
<div>
  <mu-dialog :open="status"
             title="信息设置"
             @close="close"
             :dialogClass="'dialog-bg'">
    <mu-text-field :label="dialogInfo.title" v-model="dialogInfo.text" labelFloat/>
    <mu-flat-button slot="actions" @click="close" primary label="取消"/>
    <mu-flat-button slot="actions" primary @click="makeSure" label="确定"/>
  </mu-dialog>
</div>
</template>

<script>
import { mapGetters } from 'vuex'

export default {
  computed: {
    ...mapGetters({
      status: 'getDialogPopupStatus',
      dialogInfo: 'getDiaglogInfo'
    })
  },
  methods: {
    close () {
      this.$store.commit('setPopupStatus', { name: 'dialog', value: false });
    },
    makeSure() {
      let data = {}
      data[this.dialogInfo.type] = this.dialogInfo.text || this.dialogInfo.default;
      this.$store.commit('setUserInfo', data);
      this.close();
      this.$store.commit('setToastMessage', '修改成功');
      this.$store.commit('setPopupStatus', { name: 'toast', value: true });
    }
  }
}
</script>
