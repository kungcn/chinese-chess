import Vue from 'vue'

// bottom popup 的状态属性

export default {
  state: {
    bottom_popup_state: false
  },
  mutations: {
    setBottomPopup(state, status) {
      state.bottom_popup_state = status;
    }
  },
  getters: {
    getBottomPopupStatus(state) {
      return state.bottom_popup_state;
    }
  },
  /*actions: {
    change(context, status) {
      context.commit('setBottomPopup', status)
    }
  }*/
}