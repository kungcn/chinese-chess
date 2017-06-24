import Vue from 'vue'

export default {
  state: {
    toast: {
      msg: ''
    }
  },
  mutations: {
    setToastMessage(state, msg) {
      state.toast.msg = msg;
    }
  },
  getters: {
    getToastMessage(state) {
      return state.toast.msg;
    }
  }
}