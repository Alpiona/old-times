package trabalho1;

public class Vereador {

		private Partido partido;
		private Coligacao coligacao;
		private String nome, num;
		private int id, votos;
		private boolean eleito;		
		
		public String getNome() {
			return nome;
		}
		public void setNome(String nome) {
			this.nome = nome;
		}

		public int getVotos() {
			return votos;
		}
		public void setVotos(int votos) {
			this.votos = votos;
		}
		public String getNum() {
			return num;
		}
		public void setNum(String num) {
			this.num = num;
		}
		public int getId() {
			return id;
		}
		public void setId(int id) {
			this.id = id;
		}
		public boolean isEleito() {
			return eleito;
		}
		public void setEleito(boolean eleito) {
			this.eleito = eleito;
		}
		public Partido getPartido() {
			return partido;
		}
		public void setPartido(Partido partido) {
			this.partido = partido;
		}
		public Coligacao getColigacao() {
			return coligacao;
		}
		public void setColigacao(Coligacao coligacao) {
			this.coligacao = coligacao;
		}

}