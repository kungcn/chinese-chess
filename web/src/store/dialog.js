import Vue from 'vue'

export default {
  state: {
    dialogInfo: {
      title: '',
      text: '',
      type: '',
      default: ''
    }
  },
  mutations: {
    setDialogInfo(state, value) {
      state.dialogInfo = value;
    }
  },
  getters: {
    getDiaglogInfo(state) {
      return state.dialogInfo;
    }
  }
}