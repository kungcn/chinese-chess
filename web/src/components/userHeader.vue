<template>
    <div id="setting-header-user"
        class="background-container"
        :style="{ backgroundImage: 'url(' + img.userbg + ')' }"
        @click="iconClickHandler">
        <div id="setting-header-user-portrait">
        <img v-if="img.usr"
                :src="img.usr"
                class="center" />
        <div class="center"
                v-if="status.usr"></div>
        </div>
        <p>{{ user.name }}</p>
    </div>
</template>

<script>
    import { mapGetters } from 'vuex'

    export default {
        computed: {
            ...mapGetters({
                user: 'getUserInfo',
                portrait: 'getPortrait'
            })
        },
        mounted() {
            this.portraitIndex = this.user.portrait
            this.setCurrPortrait();
        },
        data() {
            return {
                img: {
                    userbg: require('@/assets/pages/UserSetting/header-user.png'),
                    back_btn_press: require('@/assets/pages/UserSetting/back_btn_press.png'),
                    back_btn: require('@/assets/pages/UserSetting/back_btn.png'),
                    usr: null
                },
                status: {
                    bck: false,
                    usr: false
                }
            }
        },
        methods: {
            setCurrPortrait() {
                this.img.usr = this.portrait.items[this.portraitIndex];
            },
            iconClickHandler() {
                this.$router.push({ name: 'UserSetting' });
            }
        },
        watch: {
            'portraitIndex': 'setCurrPortrait'
        }
    }
</script>

<style scoped>
    #setting-header-user {
        height: 20vh; width: 18vh;
        position: absolute;
        left: 50%;
        transform: translate(-50%, 0);
        background: no-repeat;
        background-size: 100% 100%
    }
    #setting-header-user-portrait {
        position: absolute;
        width: 10vh; height: 10vh;
        left: 50%; top: 8%;
        border-radius: 100%;
        transform: translate(-50%, 0);
        background-color: #d0b399
    }
    #setting-header-user-portrait > img {
        width: 90%; height: 90%;
        border-radius: 100%;
    }
    #setting-header-user-portrait > div {
        width: 100%; height: 100%;
        border-radius: 100%;
        background-color: rgba(0, 0, 0, 0.3)
    }
    #setting-header-user > p {
        position: relative;
        height: 25%;
        color: #d0b399;
        margin: 0;
        text-align: center;
        top: 63%;
    }
    .center {
        position: absolute;
        left: 50%; top: 50%;
        transform: translate(-50%, -50%);
    }
</style>