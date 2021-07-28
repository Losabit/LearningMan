const API_URL = "https://b4xcv1e397.execute-api.eu-west-3.amazonaws.com/dev"


let app = new Vue({
    el: "#app",
    data: {
        users: [],
        parties: [],
        filter: "all",
        components: {
            loader: loader
        },
    },
    async beforeCreate(){
        this.users = await fetch(`${API_URL}/user`).then(resp => resp.json())
        this.parties = await fetch(`${API_URL}/partie`).then(resp => resp.json())
        /*this.users = users.map(x => {
            return {
                token: x.token.S,
                pseudo: x.pseudo.S
            }
        })*/


    },
    updated: function () {
        this.$nextTick(function () {
            document.getElementById("overlay").style['display'] = "none"
        })
    },
    computed: {
        getNumberOfDead(){
            let count = 0
            this.parties.forEach(partie => {
                if(partie['isDead']){
                    ++count
                }
            })
            return count
        },

    },
    methods: {
        getPseudoByToken(token) {
            let pseudo = token;
            this.users.forEach(user => {
                if(token === user['token']){
                    pseudo = user['pseudo']
                }
            })
            return pseudo
        },
        getPartiesFiltered(){
            let filter = this.filter
            let res = []
            this.parties.forEach(partie => {
                switch(filter){
                    case 'all':
                        res.push(partie)
                        break
                    case 'players':
                        if(!partie['playerType']) res.push(partie)
                        break
                    case 'ia':
                        if(partie['playerType']) res.push(partie)
                }
            })
            return res.sort((a, b) => (a.scoreTotal < b.scoreTotal) ? 1 : -1).slice(0, 100)
        },
        getPlaytime(playtime){
            let res = ""
            let seconds = parseInt(playtime, 10)
            let hours = Math.floor(seconds / 3600)
            let minutes = Math.floor((seconds - (hours * 3600)) / 60)
            seconds = seconds - (hours * 3600) - (minutes * 60)

            if(hours > 0){ res += hours + "h"}
            if(minutes > 0){ res += minutes + "m"}
            res += seconds + "s"
            return res
        },
        generateAndDownloadFile(model, pseudo){
            let file = new Blob([model], {type: 'text/plain'})
            let a = document.createElement('a')
            document.body.appendChild(a)
            a.style['display'] = "none"
            a.href = window.URL.createObjectURL(file)
            a.download = pseudo + '.model'
            a.click()
        }
    }
})