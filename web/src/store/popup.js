import Vue from 'vue'

// bottom popup 的状态属性

export default {
  state: {
    portrait_popup_status: false,
    gender_popup_status: false,
    region_popup_status: false,
    dialog_popup_status: false,
    toast_popup_status: false
  },
  mutations: {
    setPopupStatus(state, data) {
      // console.log(value, name, state[name + '_popup_status']);
      if (!Array.isArray(data))
        data = [ data ]
      data.forEach(({ name, value }) => {
        state[name + '_popup_status'] = value;
      })
    }
  },
  getters: {
    getPortraitPopupStatus(state) {
      return state.portrait_popup_status;
    },
    getGenderPopupStatus(state) {
      return state.gender_popup_status;
    },
    getRegionPopupStatus(state) {
      return state.region_popup_status;
    },
    getDialogPopupStatus(state) {
      return state.dialog_popup_status;
    },
    getToastPopupStatus(state) {
      return state.toast_popup_status;
    }
  },
  /*actions: {
    change(context, status) {
      context.commit('setBottomPopup', status)
    }
  }*/
}