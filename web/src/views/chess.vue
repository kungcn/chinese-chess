<template>
    <div id="chess"
        :style="{ backgroundImage: 'url(' + img.bg + ')' }"
        class="background-container">
        <user-header></user-header>
        <chessboard></chessboard>
    </div>
</template>

<script>
    import { mapGetters } from 'vuex'
    import userHeader from '../components/userHeader'
    import chessboard from '../components/chessboard'

    export default {
        components: {
            'user-header': userHeader,
            'chessboard': chessboard
        },
        computed: {
            ...mapGetters({
            })
        },
        mounted() {
        },
        data() {
            return {
                img: {
                    bg: require('@/../static/img/bg.png')
                },
                status: {
                    bck: false,
                    usr: false
                }
            }
        }
    }
</script>

<style scoped>
    #chess {
        position: absolute;
        width: 100%; height: 100%;
        font-size: 2rem;
    }
    .background-container {
        background: no-repeat;
        background-size: 100% 100%
    }
</style>