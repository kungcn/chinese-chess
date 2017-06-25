/* 功能函数模块 */

const LEVEL = {
  '见习': {
    '新手九级': 0,
    '新手八级': 200,
    'color': '#656d81'
  },
  '业余': {
    '业余七级': 500,
    '业余六级': 800,
    '业余五级': 1100,
    '业余四级': 1400,
    'color': '#538254'
  },
  '专业': {
    '专业三级': 1700,
    '专业二级': 1900,
    '专业一级': 2100,
    'color': '#b74546'
  }
}

/**
 * 获取水平信息，无参数则返回所有Level信息，有则返回指定Level信息
 * @param {Number} grade
 */
export const getLevelInfo = (grade) => {
  if (!grade) return LEVEL;
  let result;
  if (grade >= 0 & grade < 200)
    result = { name: '新手九级', color: '#656d81', goal: {
      grade: 200,
      name: '八级棋士'
    }}
  else if (grade >= 200 & grade < 500)
    result = { name: '新手八级', color: '#656d81', goal: {
      grade: 500,
      name: '七级棋士'
    }}
  else if (grade >= 500 & grade < 800)
    result = { name: '业余七级', color: '#538254', goal: {
      grade: 800,
      name: '六级棋士'
    }}
  else if (grade >= 800 & grade < 1100)
    result = { name: '业余六级', color: '#538254', goal: {
      grade: 1100,
      name: '五级棋士'
    }}
  else if (grade >= 1100 & grade < 1400)
    result = { name: '业余五级', color: '#538254', goal: {
      grade: 1400,
      name: '四级棋士'
    }}
  else if (grade >= 1400 & grade < 1700)
    result = { name: '业余四级', color: '#538254', goal: {
      grade: 1700,
      name: '三级棋士'
    }}
  else if (grade >= 1700 & grade < 1900)
    result = { name: '专业三级', color: '#b74546', goal: {
      grade: 1900,
      name: '二级棋士'
    }}
  else if (grade >= 1900 & grade < 2100)
    result = { name: '专业二级', color: '#b74546', goal: {
      grade: 2100,
      name: '一级棋士'
    }}
  else if (grade >= 2100)
    result = { name: '专业一级', color: '#b74546' }
  return result
}