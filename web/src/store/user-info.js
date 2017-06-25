import Vue from 'vue'

/* 保存用户信息 */

export default {
  state: {
    user: {
      id: '20735793',
      level: '九级棋士',
      name: '冰茶浓',
      portrait: 2,
      gender: '男',
      region: {
        province: '广东',
        city: '广州'
      },
      sign: '这人很懒，什么都没留下',
      phone: null,
      gameDetail: {
        sum: 30,
        win: 23,
        loss: 7
      },
      gameDetail: {
        grade: 150,
        month: {
          last: { win: 10, loss: 2, tie: 5 },
          curr: { win: 15, loss: 9, tie: 9 },
          all:  { win: 95, loss: 15, tie: 15 }
        }
      }
    }
  },
  mutations: {
    setUserInfo(state, info) {
      state.user = {
        id: state.user.id,
        level: info.level || state.user.level,
        name: info.name || state.user.name,
        portrait: info.portrait || state.user.portrait,
        gender: info.gender || state.user.gender,
        region: info.region || state.user.region,
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
    },
    getUserRegion(state) {
      return state.user.region;
    }
  }
}