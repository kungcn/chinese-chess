<template>
    <div id="chess"
        :style="{ backgroundImage: 'url(' + img.bg + ')' }"
        class="background-container">
        <user-header></user-header>
    </div>
</template>

<script>
    import { mapGetters } from 'vuex'
    import userHeader from '../components/userHeader'

    export default {
        components: {
            'user-header': userHeader
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
        },
        methods: {

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