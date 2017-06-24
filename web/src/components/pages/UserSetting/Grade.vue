<template>
<div id="user-setting" 
:style="{ backgroundImage: 'url(' + img + ')' }"
class="background-container">
  <v-header></v-header>
  <div class = "grade_border">
    新手{{ grade }}级 {{ point }}积分
  </div>
  <div class = "grade_description">
    <mu-raised-button label="等级说明" @click="open('bottom')"/>
    <mu-popup position="bottom" popupClass="demo-popup-bottom" :open="bottomPopup" @close="close('bottom')">
      <mu-appbar title="弹出">
        <mu-flat-button slot="right" label="关闭" color="white" @click="close('bottom')"/>
      </mu-appbar>
      <mu-content-block>
        <p>
          棋力等级评测对照国家棋力评测系统，具有极高的权威性。
        </p>
        <div>
          <mu-table>
            <mu-tbody>
              <mu-tr>
                <mu-td class = 'grade_new'> 新手九级</mu-td>
                <mu-td class = 'grade_new'>0积分</mu-td>
              </mu-tr>
              <mu-tr>
                <mu-td class = 'grade_new'>新手八级</mu-td>
                <mu-td class = 'grade_new'>200积分</mu-td>
              </mu-tr>
              <mu-tr>
                <mu-td class = 'grade_middle'>业余七级</mu-td>
                <mu-td class = 'grade_middle'>500积分</mu-td>
              </mu-tr>
              <mu-tr>
                <mu-td class = 'grade_middle'>业余六级</mu-td>
                <mu-td class = 'grade_middle'>800积分</mu-td>
              </mu-tr>
              <mu-tr>
                <mu-td class = 'grade_middle'>业余五级</mu-td>
                <mu-td class = 'grade_middle'>1100积分</mu-td>
              </mu-tr>
              <mu-tr>
                <mu-td class = 'grade_middle'>业余四级</mu-td>
                <mu-td class = 'grade_middle'>1400积分</mu-td>
              </mu-tr>
              <mu-tr>
                <mu-td class = 'grade_top'>专业三级</mu-td>
                <mu-td class = 'grade_top'>1700积分</mu-td>
              </mu-tr>
              <mu-tr>
                <mu-td class = 'grade_top'>专业二级</mu-td>
                <mu-td class = 'grade_top'>1900积分</mu-td>
              </mu-tr>
              <mu-tr>
                <mu-td class = 'grade_top'>专业一级</mu-td>
                <mu-td class = 'grade_top'>2100积分</mu-td>
              </mu-tr>
            </mu-tbody>
          </mu-table>


        </div>
      </mu-content-block>
    </mu-popup>
  </div>
  
  <mu-tabs id = "grade_tab":value="activeTab" @change="handleTabChange">
    <mu-tab value="thismonth" title="本月战绩" class='grade_tabs'/>
    <mu-tab value="lastmonth" title="上月战绩" class='grade_tabs'/>
    <mu-tab value="all" title="总战绩" class='grade_tabs'/>
  </mu-tabs>
  
  <div v-if="activeTab === 'thismonth'">
    <div>
      <div class = 'grade_item'>
        <div>胜利</div>
        <div>{{ thismonthwin }}局</div>
      </div>
      <div class = 'grade_item'>
        <div>失败</div>
        <div>{{ thismonthfail }}局</div>
      </div>
      <div class = 'grade_item'>
        <div>和棋</div>
        <div>{{ thismonthpie }}局</div>
      </div>
    </div>
  </div>
  <div v-if="activeTab === 'lastmonth'">
    <div>
      <div class = 'grade_item'>
        <div>胜利</div>
        <div>{{ lastmonthwin }}局</div>
      </div>
      <div class = 'grade_item'>
        <div>失败</div>
        <div>{{ lastmonthfail }}局</div>
      </div>
      <div class = 'grade_item'>
        <div>和棋</div>
        <div>{{ lastmonthpie }}局</div>
      </div>
    </div>
  </div>
  <div v-if="activeTab === 'all'">
    <div>
      <div class = 'grade_item'>
        <div>胜利</div>
        <div>{{ allwin }}局</div>
      </div>
      <div class = 'grade_item'>
        <div>失败</div>
        <div>{{ allfail }}局</div>
      </div>
      <div class = 'grade_item'>
        <div>和棋</div>
        <div>{{ allpie }}局</div>
      </div>
    </div>
  </div>

</div>
</template>

<script>

import vHeader from './children/Header'
import vContent from './children/Content'
import vBottomPopup from './children/BottonPopup'

export default {
  components: {
    vHeader, vContent,  vBottomPopup
  },
  data() {
    return {
      bottomPopup:false,
      img: require('@/assets/pages/UserSetting/bg.png'),
      user: {
        type: 1,
        account: '陈海城'
      },
      point:150,
      grade:9,

      allwin:0,
      allfail:0,
      allpie:0,
      
      lastmonthwin:0,
      lastmonthfail:0,
      lastmonthpie:0,

      thismonthwin:0,
      thismonthfail:0,
      thismonthpie:0,

      activeTab: 'all'
    }
  },
  methods:{
    open (position) {
      this[position + 'Popup'] = true
    },

    close (position) {
      this[position + 'Popup'] = false
    },

    handleTabChange (val) {
      this.activeTab = val
    }
  }
  
}
</script>

<style>
  .grade_border {
    width: 60%;
    margin-left: 20%;
    margin-bottom: 2%;
    text-align: center;
    border: 0.01vw solid #990000;
    border-radius: 50%;
  }

  .demo-menu {
      display: inline-block;
      margin: 16px 32px 16px 0;
  }

  .demo-popup-bottom {
    font-size: 1pt;
    width: 100%;
    max-width: 375px;
  }

  .grade_new {
    color:blue;
  }

  .grade_middle {
    color:green;
  }

  .grade_top {
    color:red;
  }

  .grade_tabs {
    background-color: none;
  }

  #grade_tabs {
    background-color: red;
  }

  .grade_description {
    margin-top: 10%; 
    margin-bottom: 50%;
  }

  .grade_item {
    margin-top: 2%;
    width: 33%;
    float: left;
  }

</style>
