import Vue from 'vue'

// bottom popup 的状态属性

export default {
  state: {
    portrait_popup_status: false,
    gender_popup_status: false
  },
  mutations: {
    setPopupStatus(state, { name, value }) {
      //console.log('click2', value, name, state[name + '_popup_status']);
      state[name + '_popup_status'] = value;
    }
  },
  getters: {
    getPortraitPopupStatus(state) {
      return state.portrait_popup_status;
    },
    getGenderPopupStatus(state) {
      return state.gender_popup_status;
    }
  },
  /*actions: {
    change(context, status) {
      context.commit('setBottomPopup', status)
    }
  }*/
}