import Vue from 'vue'

/* 保存用户信息 */

export default {
  state: {
    user: {
      id: '20735793',
      level: '九级棋士',
      name: '叶泽坤',
      portrait: 2,
      gender: '男',
      province: '广东省',
      sign: '这人很懒，啥都没写',
      phone: null,
      gameDetail: {
        sum: 30,
        win: 23,
        loss: 7
      }
    }
  },
  mutations: {
    setUserInfo(state, info) {
      state.user = {
        level: info.level || state.user.level,
        name: info.name || state.user.name,
        portrait: info.portrait || state.user.portrait,
        gender: info.gender || state.user.province,
        province: info.province || state.user.province,
        sign: info.sign || state.user.sign,
        phone: info.phone || state.user.phone,
        gameDetail: info.gameDetail || state.user.gameDetail
      }
    },
    setPortrait(state, ptr) {
      state.user.portrait = ptr;
    }
  },
  getters: {
    getUserInfo(state) {
      return state.user;
    },
    getPortraitIndex(state) {
      return state.user.portrait;
    }
  }
}