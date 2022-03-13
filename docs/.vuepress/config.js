module.exports = {
  title: 'LoRaWAN Workshop',
  description: 'Introductie tot LoRaWAN aan de hand van een STEM workshop',
  themeConfig: {
    navbar: [
      {text: 'VIVES', link: 'https://www.vives.be'}
    ],
    repo: 'https://github.com/99-bugs/lorawan-twin-workshop',
    docsDir: 'docs',
    docsBranch: 'master',
    sidebar: [
      {
        text: 'De things',
        children: [
          {
            text: 'De SODAQ ExpLoRer',
            link: '/sodaq-explorer/'
          },
          {
            text: 'Datacaptatie',
            link: '/data-capture/'
          },
        ]
      },
      {
        text: 'Het Internet',
        children: [
          
          {
            text: 'LoRaWAN',
            link: '/lorawan/',
          },
          {
            text: 'MQTT',
            link: '/mqtt/'
          },
        ]
      },
      {
        text: 'De applicatie',   // required
        children: [
          {
            text: 'Node-RED',
            link: '/node-red/'
          },
          {
            text: 'Node-RED Dashboard',
            link: '/node-red-dashboard/'
          },
          {
            text: 'InfluxDB',
            link: '/influxdb/'
          },
        ]
      },
      {
        text: 'Grove Sensoren',   // required
        link: '/sensors/',
        children: [
          {
            text: 'Een Push Button',
            link: '/sensors/push_button/'
          },
          {
            text: 'Een Rotary Sensor',
            link: '/sensors/rotary-sensor/'
          },
        ]
      },

    ],
  },
  serviceWorker: true,
  plugins: [],
}