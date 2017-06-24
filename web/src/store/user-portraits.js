import Vue from 'vue'

/* 所有头像以及当前头像信息 */

export default {
  // 单例化数据
  state: {
    protrait: {
      items: (function() {
        let result = [];
        for (let i = 0; i < 18; ++i) {
          result.push(require(`@/assets/portraits/${i}.png`))
        }
        return result;
      })(),
      size: 19,
      curr: 5
    }
  },
  // 修改状态的事件回调函数
  mutations: {
    setCurr(state, ptr) {
      if (ptr < state.protrait.size)
        state.protrait.curr = ptr;
    }
  },
  // 状态获取函数
  getters: {
    getProtrait(state) {
      return state.protrait;
    }
  },
  // 分发修改状态的事件
  actions: {
    cityChange(context, curr) {
      context.commit('setCurr', curr);
    }
  }
}