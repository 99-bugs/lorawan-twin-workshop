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
          {
            text: 'Grove sensoren',
            link: '/sensors/',
            collapsible: true,
            children: [
              '/sensors/push_button/',
              '/sensors/switch/',
              // '/sensors/q_touch/',
              // '/sensors/rfid/',
              // '/sensors/motion-sensor/',
              // '/sensors/rotary-sensor/',
              // '/sensors/tph-sensor/',
            ]
          }
        ]
      },
      {
        text: 'Het Internet',
        children: [
          '/lorawan/',
          '/mqtt/'
        ]
      },
      {
        text: 'De applicatie',   // required
        children: [
          '/node-red/',
          '/node-red-dashboard/',
        ]
      },
    ],
  },
  serviceWorker: true,
  plugins: [],
}